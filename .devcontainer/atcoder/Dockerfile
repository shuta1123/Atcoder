FROM gcc:14.2.0-bookworm

ARG USERNAME=vscode
ARG USER_UID=1000
ARG USER_GID=$USER_UID
ARG LIBRARY_PATH=/workspace/competitive/library
ARG NVM_VERSION=v0.40.3

##
# create vscode user
##
RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME \
    && apt-get update \
    && apt-get install -y --no-install-recommends sudo \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

##
# install gdb
##
RUN apt-get update \
    && apt-get install -y --no-install-recommends gdb \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

##
# install online-judge-tools
##
RUN apt-get update \
    && apt-get install -y --no-install-recommends pipx \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

USER $USERNAME
RUN pipx ensurepath \
    && pipx install online-judge-tools \
    && pipx inject online-judge-tools setuptools \
    && pipx install online-judge-verify-helper \
    && pipx inject online-judge-verify-helper setuptools \
    && pipx install online-judge-template-generator \
    && pipx inject online-judge-template-generator setuptools

##
# patch online-judge-tools (AtCoder HTML parse bug)
# - assert parsed_memory_limit  → skip if None
# - parsed_memory_limit.group(2) → fallback to "256" if not a match object
##
RUN python3 - << 'EOF'
import glob, pathlib, sys

files = glob.glob('/home/vscode/.local/pipx/**/*.py', recursive=True)
targets = [f for f in files if 'onlinejudge' in f and f.endswith('atcoder.py')]
if not targets:
    print("ERROR: atcoder.py not found", file=sys.stderr)
    sys.exit(1)

path = pathlib.Path(targets[0])
text = path.read_text()

text = text.replace(
    'assert parsed_memory_limit',
    'parsed_memory_limit = parsed_memory_limit  # assert removed by patch'
)
text = text.replace(
    'memory_limit_value = parsed_memory_limit.group(2)',
    'memory_limit_value = parsed_memory_limit.group(2) if hasattr(parsed_memory_limit, "group") else "256"'
)
text = text.replace(
    'memory_limit_unit = parsed_memory_limit.group(3)',
    'memory_limit_unit = parsed_memory_limit.group(3) if hasattr(parsed_memory_limit, "group") else "MB"'
)

path.write_text(text)
print(f"Patched: {path}")
EOF

##
# install atcoder-cli
##
SHELL ["/bin/bash", "-c"]
RUN curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/$NVM_VERSION/install.sh | bash \
    && . $HOME/.nvm/nvm.sh \
    && nvm install node \
    && npm install -g npm \
    && npm install -g atcoder-cli