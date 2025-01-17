#include <cstring>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <vector>

#include "poggles/shader.h"

auto poggles::compileShader(shader_id shader, std::filesystem::path path)
    -> bool
{
  // read shader source
  std::string source_string;
  std::ifstream file;

  // ensure ifstream objects can throw exceptions:
  file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    // open file
    file.open(path.string());
    std::stringstream source_stream;

    // read file buffer contents into stream
    source_stream << file.rdbuf();

    // close file handler
    file.close();

    // convert stream into string
    source_string = source_stream.str();
  } catch (std::ifstream::failure const&) {
    std::string error_msg;
    // TODO: get this working generally
    // #ifdef DGGS_VISUALSTUDIO
    // error_msg.resize(94); //
    // https://developercommunity.visualstudio.com/t/strerrorlen-s-is-not-supported/160287
    // strerror_s(error_msg.data(), error_msg.size(), errno);
    // #else
    // #endif

    error_msg = strerror(errno);
    std::cerr << "[SHADER] reading " << path.string() << ":\n"
              << error_msg << std::endl;
    return false;
  }

  GLchar const* source_code = source_string.c_str();

  // compile shader
  glShaderSource(shader, 1, &source_code, nullptr);
  glCompileShader(shader);

  // Always log the info, just change the severity
  // based on whether it's an error or not
  GLint log_length = -1;
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
  std::string log;
  log.resize(static_cast<size_t>(log_length));
  glGetShaderInfoLog(shader, log_length, nullptr, log.data());

  // check for errors
  GLint success = -1;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (success == 0) {
    std::cerr << "[SHADER] compilation log " << path.string() << ":\n"
              << log << std::endl;
  } else {
    std::cerr << "[SHADER] compilation log " << path.string() << ":\n"
              << log << std::endl;
  }
  return success != 0;
}