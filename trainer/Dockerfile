FROM node:22-bookworm-slim AS web-build

WORKDIR /build
COPY package.json package-lock.json ./
RUN npm ci
COPY web ./web
RUN npm run build

FROM debian:bookworm-slim AS zig-build

ARG TARGETARCH
ARG ZIG_VERSION=0.16.0

RUN apt-get update \
    && apt-get install -y --no-install-recommends ca-certificates curl build-essential xz-utils \
    && rm -rf /var/lib/apt/lists/* \
    && case "${TARGETARCH}" in \
         amd64) zig_arch="x86_64" ;; \
         arm64) zig_arch="aarch64" ;; \
         *) echo "Unsupported Docker architecture: ${TARGETARCH}" >&2; exit 1 ;; \
       esac \
    && curl -fsSL "https://ziglang.org/download/${ZIG_VERSION}/zig-${zig_arch}-linux-${ZIG_VERSION}.tar.xz" -o /tmp/zig.tar.xz \
    && mkdir -p /opt/zig \
    && tar -xJf /tmp/zig.tar.xz --strip-components=1 -C /opt/zig \
    && rm /tmp/zig.tar.xz

ENV PATH="/opt/zig:${PATH}"
WORKDIR /build
COPY build.zig build.zig.zon ./
COPY src ./src
COPY --from=web-build /build/web/dist ./web/dist
RUN zig build -Doptimize=ReleaseSafe

FROM debian:bookworm-slim AS runtime

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
       ca-certificates curl git g++ clangd clang-format ripgrep fd-find tmux unzip \
    && rm -rf /var/lib/apt/lists/*

ARG TARGETARCH
ARG NVIM_VERSION=v0.11.3

RUN case "${TARGETARCH}" in \
      amd64) nvim_arch="x86_64" ;; \
      arm64) nvim_arch="arm64" ;; \
      *) echo "Unsupported architecture: ${TARGETARCH}" >&2; exit 1 ;; \
    esac \
    && curl -fsSL \
       "https://github.com/neovim/neovim/releases/download/${NVIM_VERSION}/nvim-linux-${nvim_arch}.tar.gz" \
       -o /tmp/nvim.tar.gz \
    && tar -xzf /tmp/nvim.tar.gz -C /opt \
    && ln -s "/opt/nvim-linux-${nvim_arch}/bin/nvim" /usr/local/bin/nvim \
    && rm /tmp/nvim.tar.gz


WORKDIR /opt/dsa-trainer
COPY --from=zig-build /build/zig-out/bin/dsa-trainer ./bin/dsa-trainer
COPY --from=web-build /build/web/index.html ./web/index.html
COPY --from=web-build /build/web/styles.css ./web/styles.css
COPY --from=web-build /build/web/dist ./web/dist
COPY nvim ./nvim
COPY nvim-config ./nvim-config
COPY docker/entrypoint.sh ./entrypoint.sh
RUN chmod +x ./entrypoint.sh

ENV XDG_CONFIG_HOME=/opt/dsa-trainer/nvim-config \
    XDG_DATA_HOME=/opt/dsa-trainer/nvim-data

RUN nvim --headless "+Lazy! sync" +qa

ENV DSA_ROOT=/workspace \
    PORT=8080 \
    TRAINER_PATH=/opt/dsa-trainer \
    BIND_HOST=0.0.0.0

VOLUME ["/workspace"]
EXPOSE 8080
ENTRYPOINT ["/opt/dsa-trainer/entrypoint.sh"]
