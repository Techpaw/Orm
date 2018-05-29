from conans import ConanFile, CMake, tools

class OrmConan(ConanFile):
    name = "Orm"
    version = "0.1"
    license = "MIT"
    url = "https://github.com/Techpaw/Orm.git"
    description = "Experimental ORM for cpp projects (now supports Postgres only)"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = "shared=False"
    generators = "cmake"
    exports_sources = "include/*"

    def source(self):
        self.run("git clone https://github.com/Techpaw/Orm.git")
        self.run("cd orm && git checkout stable")

    def package(self):
        self.copy("*.hpp", dst="include", src="orm/include")

    def package_info(self):
        self.cpp_info.libs = ["orm"]
