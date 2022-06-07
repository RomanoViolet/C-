#
# Ubuntu Dockerfile
#
# https://github.com/dockerfile/ubuntu
# https://blobfolio.com/2018/12/using-docker-as-a-build-environment/

# Pull base image.
FROM ubuntu:22.04

# On single RUN command: https://coderwall.com/p/4g8znw/things-i-learned-while-writing-a-dockerfile
LABEL CPPDocker.version="0.2-beta"
LABEL vendor="Devendra Rai, rai.devendra@yahoo.co.uk"
LABEL CPPDocker.release-date="2019-10-03"
LABEL CPPDocker.version.is-production="No"

ARG GTEST_TAG=release-1.11.0
ARG USERNAME=dockeruser
ARG USER_UID=1000
ARG USER_GID=$USER_UID

# Tell debian that we are running non-interactively
ENV DEBIAN_FRONTEND=noninteractive

# Install Core components.
RUN \
  sed -i 's/# \(.*multiverse$\)/\1/g' /etc/apt/sources.list && \
  apt-get update && \
  apt-get -qqy upgrade && \
  apt-get -y install --no-install-recommends apt-utils dialog 2>&1 && \
  apt-get install -y build-essential && \
  apt-get install -y software-properties-common && \
  apt-get install -y sudo && \
  apt-get install -qqy libz-dev && \
  apt-get install -qqy gnupg && \
  apt-get install -qqy curl && \
  apt-get install -qqy net-tools && \
  apt-get install -qqy wget && \
  apt-get install -qqy global exuberant-ctags && \
  apt-get install -qqy git git-lfs && \
  apt-get install -qqy gcc && \
  apt-get install -qqy g++ && \
  apt-get install -qqy lcov && \
  apt-get install -qqy bash && \
  apt-get install -qqy gdb && \
  apt-get install -qqy cppcheck && \
  apt-get install -qqy global exuberant-ctags && \
  apt-get install -qqy git && \
  apt-get install -qqy git git-lfs && \
  apt-get install -qqy xz-utils && \
  apt-get install -qqy apt-transport-https && \
  apt-get install -qqy python3 python3-pip && \
  apt-get install -qqy python3-jinja2 && \
  apt-get install -qqy libboost-system-dev && \
  apt-get install -qqy libboost-thread-dev && \
  apt-get install -qqy libboost-filesystem-dev && \
  apt-get install -qqy cmake cmake-extras && \
  apt-get install -qqy make && \
  apt-get install -qqy locales && \
  apt-get install -qqy tree && \
  git clone -q https://github.com/google/googletest.git /googletest  --branch ${GTEST_TAG} --single-branch && \
  cd /googletest && \
  #git lfs install --system --skip-repo && \
  #git reset --hard $GTESTCOMMITID && \
  mkdir -p /googletest/build  && \
  cd /googletest/build  && \
  cmake .. && make && make install  && \
  cd / && rm -rf /googletest && \
  #
  # LLVM Repository
  bash -c "$(wget -O - https://apt.llvm.org/llvm.sh)"

# Python Requirements
COPY requirements-py3.txt .
RUN \
  pip3 install -r requirements-py3.txt && \
  rm requirements-py3.txt

RUN \
  apt-get purge -y --auto-remove build-essential && \
  apt-get purge -y --auto-remove software-properties-common && \
  apt-get purge -y --auto-remove curl wget && \
  apt-get purge -y --auto-remove xz-utils && \
  apt-get purge -y --auto-remove python3-pip && \
  apt-get purge -y --auto-remove apt-transport-https && \
  apt-get autoremove -y && \
  apt-get clean && \
  rm -rf /var/lib/apt/lists/* && \
  #update-alternatives --install /usr/bin/clang clang /usr/bin/clang-8 100 && \
  #update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-8 100 && \
  #update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-8 100 && \
  #update-alternatives --install /usr/bin/clangd clangd /usr/bin/clangd-8 100 && \
  #
  # Setup locales
  sed -i -e 's/# en_US.UTF-8 UTF-8/en_US.UTF-8 UTF-8/' /etc/locale.gen && \
  dpkg-reconfigure --frontend=noninteractive locales && \
  update-locale LANG=en_US.UTF-8 && \
  #
  # Add non-admin user
  groupadd --gid $USER_GID $USERNAME && \
  useradd -s /bin/bash --uid $USER_UID --gid $USER_GID -m $USERNAME && \
  echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME && \
  chmod 0440 /etc/sudoers.d/$USERNAME && \
  #
  # Add files for convenience.
  #ADD root/.bashrc /home/dockeruser/.bashrc
  #ADD root/.scripts /home/dockeruser/.scripts
  #
  #
  # Make sure that all file in /home/dockeruser are owned by dockeruser
  chown -R dockeruser /home/dockeruser
#ENV HOME /home/dockeruser && \
#

# Add default home for the non-admin user
WORKDIR /home/dockeruser
RUN mkdir /home/dockeruser/.config && \
  mkdir /home/dockeruser/.config/powerline-shell && \
  mkdir /home/dockeruser/.config/themes

ADD --chown=dockeruser Configurations/.gitconfig /home/dockeruser/.gitconfig
ADD --chown=dockeruser Configurations/.bashrc /home/dockeruser/.bashrc
ADD --chown=dockeruser Configurations/git-completion.sh /home/dockeruser/git-completion.sh
ADD --chown=dockeruser Configurations/git-prompt.sh /home/dockeruser/git-prompt.sh
COPY --chown=dockeruser Configurations/powerline-shell/ /home/dockeruser/.config/powerline-shell/
ADD --chown=dockeruser Configurations/themes/ /home/dockeruser/.config/themes/
#ADD --chown=dockeruser VSCodeExtensions/extensions /home/dockeruser/.vscode-server/extensions

ENV LANG en_US.UTF-8
ENV LANG C.UTF-8
ENV LC_ALL C.UTF-8

# Do the following as an ordinary user
USER dockeruser

RUN \
  chmod +x /home/dockeruser/.bashrc && \
  chmod +x /home/dockeruser/git-completion.sh && \
  chmod +x /home/dockeruser/git-prompt.sh
#echo 'export PATH=/clang_8/bin:$PATH' >> ~/.bashrc && \
#echo 'export LD_LIBRARY_PATH=/clang_8/lib:/usr/local/lib:$LD_LIBRARY_PATH' >> ~/.bashrc


# Define default command.
# CMD ["/bin/bash"]
