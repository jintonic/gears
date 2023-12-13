#!/bin/bash
# add gears directory to PATH
GEARS="$(cd "$(dirname "${BASH_SOURCE[0]}")" >/dev/null 2>&1 && pwd)"
export PATH=$GEARS:$PATH
