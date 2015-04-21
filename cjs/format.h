namespace kennykerr {
	// Taken from: https://msdn.microsoft.com/en-us/magazine/dn913181.aspx
	template <typename T>
	T Argument(T value) 
	{
		return value;
	}

	template <typename T>
	T const * Argument(std::basic_string<T> const & value) 
	{
		return value.c_str();
	}

	template <typename ... Args>
	int StringPrint(char * const buffer,
		size_t const bufferCount,
		char const * const format,
		Args const & ... args) 
	{
		int const result = snprintf(buffer,
			bufferCount,
			format,
			Argument(args) ...);
		if (result == -1) {
			return snprintf(nullptr, 0, format, Argument(args)...);
		}

		return result;
	}

	template <typename ... Args>
	int StringPrint(wchar_t * const buffer,
		size_t const bufferCount,
		wchar_t const * const format,
		Args const & ... args) 
	{
		int const result = swprintf(buffer,
			bufferCount,
			format,
			Argument(args) ...);
		if (result == -1) {
			return swprintf(nullptr, 0, format, Argument(args)...);
		}
		return result;
	}

	template <typename T, typename ... Args>
	void Format(std::basic_string<T> & buffer,
		T const * const format,
		Args const & ... args)
	{
		size_t const size = StringPrint(&buffer[0],
			buffer.size() + 1,
			format,
			args ...);
		if (size > buffer.size())
		{
			buffer.resize(size);
			StringPrint(&buffer[0], buffer.size() + 1, format, args ...);
		}
		else if (size < buffer.size())
		{
			buffer.resize(size);
		}
	}
}
