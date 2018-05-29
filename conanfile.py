from conans import ConanFile, CMake, tools

class OrmConan(ConanFile):
    name = "Orm"
    version = "0.1"
    license = "MIT"
    url = "https://github.com/Techpaw/Orm.git"
    description = "Experimental ORM for cpp projects (now supports Postgres only)"
    options = {"shared": [True, False]}
    default_options = "shared=False"
    generators = "cmake"
    exports_sources = "include/*"
    no_copy_source = True
    requires = "boost_lexical_cast/1.65.1@bincrafters/stable", \
               "libpqxx/6.2.0@trigger-happy/testing"

    def source(self):
        self.run("git clone https://github.com/Techpaw/Orm.git")
        self.run("cd orm && git checkout stable")

    def package(self):
        self.copy("*.hpp", dst="include", src="orm/include")

    def package_id(self):
        self.info.header_only()
