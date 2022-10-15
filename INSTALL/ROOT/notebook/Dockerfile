FROM physino/root

# jupyter notebook to run ROOT and python scripts
# https://root-forum.cern.ch/t/failed-to-import-root-in-jupyter-notebook-in-docker-fedora-36/51517/2
RUN  dnf install -y python3-jupyroot root-graf-gpadv7 \
  && dnf clean all && rm -fr /var/cache/* \
  && pip install uproot awkward --no-cache-dir

