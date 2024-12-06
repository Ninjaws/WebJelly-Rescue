FROM gcc:latest as base

FROM base as development

RUN apt-get update \
    && apt-get install -y \
    entr \
    cmake \
    libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev \
    libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev \
    sudo \
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

RUN git clone https://github.com/emscripten-core/emsdk.git && \
    cd emsdk && \
    ./emsdk install latest && \
    ./emsdk activate latest && \
    cd ..

RUN echo 'source "/app/emsdk/emsdk_env.sh"' >> $HOME/.bash_profile
# RUN source "/app/emsdk/emsdk_env.sh"

RUN git clone https://github.com/raysan5/raylib.git raylib \
    && cd raylib \
    && mkdir build && cd build \
    && cmake -DBUILD_SHARED_LIBS=OFF -DRAYLIB_STATIC=ON .. \
    && make \
    && sudo make install \
    && cd ..

# RUN mkdir dist
# && cmake -DBUILD_SHARED_LIBS=ON .. \

ENV LD_LIBRARY_PATH=/app/raylib/build/raylib

# RUN cd raylib/src
# # Builds raylib for WebAssembly usage
# RUN emcc -c rcore.c -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2
# RUN emcc -c rshapes.c -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2
# RUN emcc -c rtextures.c -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2
# RUN emcc -c rtext.c -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2
# RUN emcc -c rmodels.c -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2
# RUN emcc -c utils.c -Os -Wall -DPLATFORM_WEB
# RUN emcc -c raudio.c -Os -Wall -DPLATFORM_WEB
# RUN emar rcs libraylib.a rcore.o rshapes.o rtextures.o rtext.o rmodels.o utils.o raudio.o
# RUN cd ../..

RUN cd raylib/src && \
    source /app/emsdk/emsdk_env.sh && \
    emcc -c rcore.c -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2 && \
    emcc -c rshapes.c -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2 && \
    emcc -c rtextures.c -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2 && \
    emcc -c rtext.c -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2 && \
    emcc -c rmodels.c -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2 && \
    emcc -c utils.c -Os -Wall -DPLATFORM_WEB && \
    emcc -c raudio.c -Os -Wall -DPLATFORM_WEB && \
    emar rcs libraylib.a rcore.o rshapes.o rtextures.o rtext.o rmodels.o utils.o raudio.o && \
    cd ../..

CMD ["bash"]
