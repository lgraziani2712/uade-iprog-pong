from conan import ConanFile
from conan.tools.cmake import cmake_layout


class PongRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("sdl/2.32.2")

    def layout(self):
        cmake_layout(self)
