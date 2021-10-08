FROM ubuntu:focal AS riscv_dev_env 

ENV NODE_VERSION=14.18.0
ENV NVM_DIR=/root/.nvm
ENV XPACKS_REPO_FOLDER=/root/.xpack/repos
#ENV XPACKS_CACHE_FOLDER=/root/.xpack
ENV XPACKS_SYSTEM_FOLDER=/root/.xpack/system
#

RUN apt-get update -qq 
RUN apt install -y curl
RUN curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.38.0/install.sh | bash
RUN . "$NVM_DIR/nvm.sh" && nvm install ${NODE_VERSION}
RUN . "$NVM_DIR/nvm.sh" && nvm use v${NODE_VERSION}
RUN . "$NVM_DIR/nvm.sh" && nvm alias default v${NODE_VERSION}
ENV PATH="/root/.nvm/versions/node/v${NODE_VERSION}/bin/:${PATH}"
RUN node --version
RUN npm --version

RUN npm install --global xpm@latest
RUN xpm install --global --verbose  @xpack-dev-tools/riscv-none-embed-gcc@10.1.0-1.1.1   
ENV PATH=/root/.xpack/repos/@xpack-dev-tools/riscv-none-embed-gcc/10.1.0-1.1.1/.content/bin:/bin/:/usr/bin

RUN echo $PATH
RUN ls -l /root/.xpack/repos/@xpack-dev-tools/riscv-none-embed-gcc/10.1.0-1.1.1/.content/bin/
RUN riscv-none-embed-gcc --version

RUN apt-get install -y cmake

# Copies your code file from your action repository to the filesystem path `/` of the container
COPY docker_entrypoint.sh /docker_entrypoint.sh

# Code file to execute when the docker container starts up (`entrypoint.sh`)
ENTRYPOINT ["/docker_entrypoint.sh"]

