# -------------------------------------------------------------
# Create pongone target
# -------------------------------------------------------------
psn00bsdk_add_executable(${PONGONE_EXE_NAME} GPREL)
psn00bsdk_add_cd_image(
	${PONGONE_EXE_NAME}_iso
	${PONGONE_EXE_NAME}
	${PROJECT_SOURCE_DIR}/iso.xml
	DEPENDS ${PONGONE_EXE_NAME} ${PROJECT_SOURCE_DIR}/system.cnf
)

# -------------------------------------------------------------
# Specify compile options
# -------------------------------------------------------------
target_compile_features(${PONGONE_EXE_NAME} PRIVATE cxx_std_23)

target_compile_options(
    ${PONGONE_EXE_NAME}
    PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>: -Wall>
)

# -------------------------------------------------------------
# Add sources
# -------------------------------------------------------------
set(PONGONE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/framebuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/framebuffer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/render_buffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/render_buffer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/renderer.h
)

target_sources(${PONGONE_EXE_NAME} PRIVATE ${PONGONE_SOURCES})

