
solution ("Luagro")
	configurations { "Debug", "Release" }

	project ("Luagro")
		kind "ConsoleApp"
		language "C++"
		location "build"
		files { "src/*.cpp" }
		includedirs { "include", "/usr/include/lua5.2" }
		links ( {"lua5.2", "allegro", "allegro_image"} )

		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }
 			buildoptions { "-fPIC", "-m64", "-std=c++11" }

		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }
			buildoptions { "-fPIC", "-m64", "-std=c++11" }
