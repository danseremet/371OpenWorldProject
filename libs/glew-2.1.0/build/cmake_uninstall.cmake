if(NOT EXISTS "/media/danseremet/DATA/P/C-CPP/clion-workspace/COMP371LABS/Lab01_SRC/libs/glew-2.1.0/build/install_manifest.txt")
  message(FATAL_ERROR "Cannot find install manifest: /media/danseremet/DATA/P/C-CPP/clion-workspace/COMP371LABS/Lab01_SRC/libs/glew-2.1.0/build/install_manifest.txt")
endif(NOT EXISTS "/media/danseremet/DATA/P/C-CPP/clion-workspace/COMP371LABS/Lab01_SRC/libs/glew-2.1.0/build/install_manifest.txt")

if (NOT DEFINED CMAKE_INSTALL_PREFIX)
  set (CMAKE_INSTALL_PREFIX "/usr/local")
endif ()
 message(${CMAKE_INSTALL_PREFIX})

file(READ "/media/danseremet/DATA/P/C-CPP/clion-workspace/COMP371LABS/Lab01_SRC/libs/glew-2.1.0/build/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")
foreach(file ${files})
  message(STATUS "Uninstalling $ENV{DESTDIR}${file}")
  if(IS_SYMLINK "$ENV{DESTDIR}${file}" OR EXISTS "$ENV{DESTDIR}${file}")
    exec_program(
      "/usr/local/bin/cmake" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
      OUTPUT_VARIABLE rm_out
      RETURN_VALUE rm_retval
      )
    if(NOT "${rm_retval}" STREQUAL 0)
      message(FATAL_ERROR "Problem when removing $ENV{DESTDIR}${file}")
    endif(NOT "${rm_retval}" STREQUAL 0)
  else(IS_SYMLINK "$ENV{DESTDIR}${file}" OR EXISTS "$ENV{DESTDIR}${file}")
    message(STATUS "File $ENV{DESTDIR}${file} does not exist.")
  endif(IS_SYMLINK "$ENV{DESTDIR}${file}" OR EXISTS "$ENV{DESTDIR}${file}")
endforeach(file)
