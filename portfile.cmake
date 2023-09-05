vcpkg_from_github(
  OUT_SOURCE_PATH SOURCE_PATH
  REPO Luidirug3/atx-logger
  REF 8844e412e1f2d91e041ca673723d4e1273fc1729
  SHA512 32a0404d5901926e2b550ebf0fc4e9d527c407fc5e929d2482cac50a6efbf19cbb309b7736426a7fd4e8ee63726743b0659cfab1780c9921a33c1e5cb79db0eb
  HEAD_REF main
)

vcpkg_configure_cmake(
  SOURCE_PATH "${SOURCE_PATH}"
  PREFER_NINJA
)
vcpkg_install_cmake()
vcpkg_fixup_cmake_targets()

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")

file(
  INSTALL "${SOURCE_PATH}/LICENSE"
  DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}"
  RENAME copyright)