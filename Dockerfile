FROM gcc:14

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    cmake \
    make \
    ninja-build \
    git \
    wget \
    unzip \
    build-essential \
    ca-certificates \
    pkg-config \
    libssl-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace

COPY . /workspace

CMD ["/bin/bash"]
