// cjs.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "format.h"
#include "repl.h"

using namespace std;
using namespace cjs;

int _tmain(int argc, _TCHAR* argv[])
{
	jsrt::runtime runtime = jsrt::runtime::create();
	auto context = runtime.create_context();

	{
		jsrt::context::scope scope(context);

		// parse a line of javascript and return true if it's valid
		auto lineChecker = [](wstring input) -> bool {
			try {
				auto code = jsrt::context::parse(input);
				return code.is_valid();
			}
			catch (jsrt::exception) {
				return false;
			}
		};

		// run a line a javascript
		auto eval = [](wstring input) -> wstring {
			try {
				return jsrt::string::convert(
					jsrt::context::evaluate(input)).data();
			}
			catch (jsrt::error error) {
				return error.message();
			}
			catch (jsrt::script_compile_exception e) {
				wstring err;
				auto error = e.error();
				kennykerr::Format(err, L"Error (%d,%d): %ls\n\tSource: %ls",
					error.line(), error.column(), error.message(), error.source());
				return err;
			}
			catch (jsrt::exception) {
				return L"An error occurred.";
			}
		};

		return repl(L"> ").run(lineChecker, eval);
	}

	return 0;
}
