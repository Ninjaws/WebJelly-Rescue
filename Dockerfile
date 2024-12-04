FROM gcc:latest as base

FROM base as development

RUN apt-get update \
    && apt-get install -y \
    entr \
    cmake \
    libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev \
    libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev \
    sudo \
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

RUN git clone https://github.com/raysan5/raylib.git raylib \
    && cd raylib \
    && mkdir build && cd build \
    && cmake -DBUILD_SHARED_LIBS=ON .. \
    && make \
    && sudo make install \
    && cd ..

# RUN mkdir dist

ENV LD_LIBRARY_PATH=/app/raylib/build/raylib

CMD ["bash"]
