#!/usr/bin/env bash
set -e
BASEDIR=$(dirname "$0")
cd "$BASEDIR"
flatc -c -o generated Types.fbs GameInput.fbs GameOutput.fbs
cd -