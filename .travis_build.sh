#!/bin/bash

PSVSDK_URL="https://bintray.com/vitasdk/vitasdk/download_file?file_path=vitasdk-gcc-5.4-linux-compat-nightly-714786ee6e105972d6a78e912e4d1de52718dafe.tar.bz2"

function getSDK {
  echo "Download SDK:"
  curl "$PSVSDK_URL" > sdk.tar.bz2
  echo "Donwload Finished"

  echo "untar and unzip"
  mkdir psvsdk && tar jxf sdk.tar.bz2 -C psvsdk
  echo "decompressing finished"
  ls psvsdk
}

getSDK
