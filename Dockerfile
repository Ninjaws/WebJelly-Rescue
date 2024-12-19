FROM gcc:latest as base

FROM base as development

RUN apt-get update \
    && apt-get install -y \
    entr \
    cmake \
    libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev \
    libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev \
    sudo lldb \
    alsa-utils \
    && rm -rf /var/cache/apt/*


RUN groupadd -g 1000 dev && useradd -m -u 1000 -g dev dev
RUN chsh -s /bin/bash dev  # Set the default shell to bash for the dev user

WORKDIR /app
RUN chown -R dev:dev /app

RUN echo "dev ALL=(ALL) NOPASSWD: ALL" > /etc/sudoers.d/dev && \
    chmod 0440 /etc/sudoers.d/dev

# COPY scripts ./scripts
# RUN chmod +x /app/scripts/*.sh

USER dev
SHELL ["/bin/bash", "-c"]
RUN g++ --version

RUN git clone https://github.com/emscripten-core/emsdk.git libs/emsdk && \
    cd libs/emsdk && \
    ./emsdk install latest && \
    ./emsdk activate latest && \
    cd ../..

RUN echo 'source "/app/libs/emsdk/emsdk_env.sh"' >> $HOME/.bash_profile
# RUN source "/app/emsdk/emsdk_env.sh"

RUN git clone https://github.com/raysan5/raylib.git libs/raylib \
    && cd libs/raylib \
    && mkdir build && cd build \
    && cmake -DBUILD_SHARED_LIBS=OFF -DRAYLIB_STATIC=ON .. \
    && make \
    && sudo make install \
    && cd ../..

# RUN mkdir dist
# && cmake -DBUILD_SHARED_LIBS=ON .. \

ENV LD_LIBRARY_PATH=/app/libs/raylib/build/raylib

RUN cd libs/raylib/src && \
    source /app/libs/emsdk/emsdk_env.sh && \
    emcc -c rcore.c -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2 && \
    emcc -c rshapes.c -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2 && \
    emcc -c rtextures.c -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2 && \
    emcc -c rtext.c -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2 && \
    emcc -c rmodels.c -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2 && \
    emcc -c utils.c -Os -Wall -DPLATFORM_WEB && \
    emcc -c raudio.c -Os -Wall -DPLATFORM_WEB && \
    emar rcs libraylib.a rcore.o rshapes.o rtextures.o rtext.o rmodels.o utils.o raudio.o && \
    cd ../..

# CMD ["bash"]

FROM development as build

RUN mkdir dist html src include assets

COPY include include
COPY src src
COPY html html
COPY assets assets

# CMD ["tail", "-f", "/dev/null"]
# Run the production build command to generate game.js and game.wasm
RUN source /app/libs/emsdk/emsdk_env.sh && \
    emcc $(find src/ -name "*.cpp") -o dist/game.js -O3 -Wno-missing-braces \
    -I./include -I/app/libs/raylib/build/raylib/include \
    -L/app/libs/raylib/src /app/libs/raylib/src/libraylib.a \
    -s ALLOW_MEMORY_GROWTH=1 -s INITIAL_MEMORY=536870912 -s MAXIMUM_MEMORY=4294967296 \
    -s --preload-file assets@/assets -s USE_GLFW=3 -s ASSERTIONS=2 -DPLATFORM_WEB

# CMD ["tail", "-f", "/dev/null"]

FROM nginx:alpine as production

# Remove the default nginx index.html
RUN rm -rf /usr/share/nginx/html/*

# Copy the generated files from the production stage into the Nginx html directory
COPY --from=build /app/dist/ /usr/share/nginx/html/
COPY --from=build /app/html/index.html /usr/share/nginx/html/

# Expose port 80 to allow Nginx to serve the files
EXPOSE 80

# Start Nginx server
CMD ["nginx", "-g", "daemon off;"]