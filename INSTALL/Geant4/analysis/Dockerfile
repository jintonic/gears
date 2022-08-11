FROM fedora

# jupyter notebook to run ROOT and python scripts
RUN dnf update -y && dnf install -y root root-notebook \
  && dnf clean all && rm -fr /var/cache/* \
  && pip install uproot awkward
