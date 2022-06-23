

class PreprocessinatorIncludesHandler

  constructor :configurator, :tool_executor, :task_invoker, :file_path_utils, :yaml_wrapper, :file_wrapper

  # shallow includes: only those headers a source file explicitly includes

  def invoke_shallow_includes_list(filepath)
    @task_invoker.invoke_test_shallow_include_lists( [@file_path_utils.form_preprocessed_includes_list_filepath(filepath)] )
  end

  ##
  # Ask the preprocessor for a make-style dependency rule of only the headers
  # the source file immediately includes.
  #
  # === Arguments
  # +filepath+ _String_:: Path to the test file to process.
  #
  # === Return
  # _String_:: The text of the dependency rule generated by the preprocessor.
  def form_shallow_dependencies_rule(filepath)
    # change filename (prefix of '_') to prevent preprocessor from finding
    # include files in temp directory containing file it's scanning
    temp_filepath = @file_path_utils.form_temp_path(filepath, '_')

    # read the file and replace all include statements with a decorated version
    # (decorating the names creates file names that don't exist, thus preventing
    # the preprocessor from snaking out and discovering the entire include path
    # that winds through the code). The decorated filenames indicate files that
    # are included directly by the test file.
    contents = @file_wrapper.read(filepath)
    contents.gsub!( /^\s*#include\s+[\"<]\s*(\S+)\s*[\">]/, "#include \"\\1\"\n#include \"@@@@\\1\"" )
    @file_wrapper.write( temp_filepath, contents )

    # extract the make-style dependency rule telling the preprocessor to
    # ignore the fact that it can't find the included files
    command = @tool_executor.build_command_line(@configurator.tools_test_includes_preprocessor, [], temp_filepath)
    shell_result = @tool_executor.exec(command[:line], command[:options])

    return shell_result[:output]
  end

  ##
  # Extract the headers that are directly included by a source file using the
  # provided, annotated Make dependency rule.
  #
  # === Arguments
  # +make_rule+ _String_:: Annotated Make dependency rule.
  #
  # === Return
  # _Array_ of _String_:: Array of the direct dependencies for the source file.
  def extract_shallow_includes(make_rule)
    # Extract the dependencies from the make rule
    hdr_ext = @configurator.extension_header
    dependencies = make_rule.split.find_all {|path| path.end_with?(hdr_ext) }.uniq
    dependencies.map! {|hdr| hdr.gsub('\\','/') }

    # Separate the real files form the annotated ones and remove the '@@@@'
    annotated_headers, real_headers = dependencies.partition {|hdr| hdr =~ /^@@@@/ }
    annotated_headers.map! {|hdr| hdr.gsub('@@@@','') }

    # Find which of our annotated headers are "real" dependencies. This is
    # intended to weed out dependencies that have been removed due to build
    # options defined in the project yaml and/or in the headers themselves.
    annotated_headers.find_all do |annotated_header|
      # find the index of the "real" include that matches the annotated one.
      idx = real_headers.find_index do |real_header|
        real_header =~ /^(.*\/)?#{Regexp.escape(annotated_header)}$/
      end
      # If we found a real include, delete it from the array and return it,
      # otherwise return nil. Since nil is falsy this has the effect of making
      # find_all return only the annotated headers for which a real include was
      # found/deleted
      idx ? real_headers.delete_at(idx) : nil
    end.compact
  end

  def write_shallow_includes_list(filepath, list)
    @yaml_wrapper.dump(filepath, list)
  end
end
