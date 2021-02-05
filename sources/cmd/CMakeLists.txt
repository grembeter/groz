include_directories("include")

add_library(cmd STATIC
  "cmd.c" "cmd_help.c" "cmd_version.c"
  )
