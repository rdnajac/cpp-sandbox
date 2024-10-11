def define_env(env):
    """Hook for defining variables/macros/filters in the MkDocs environment."""

    @env.macro
    def source_code(file) -> str:
        """Reads the source code from a file and returns it as a string."""
        lang = "cpp"  # TODO deduce language from file extension
        with open(file, "r") as f:
            source_code = f.read()
        return f"```{lang}\n{source_code}\n```"
