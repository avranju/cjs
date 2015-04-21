#pragma once

namespace cjs {
	using namespace std;

	class repl
	{
	private:
		wstring _prompt;
		static bool s_done;

	public:
		repl(wstring prompt) :
			_prompt( prompt ) {}

		template <typename LineChecker, typename Eval>
		int run(LineChecker lineChecker, Eval eval) {
			// setup ctrl+c handling
			SetConsoleCtrlHandler((PHANDLER_ROUTINE) ctrlHandler, TRUE);

			while (!repl::s_done) {
				// show prompt
				wcout << _prompt;

				// read a line of input and check if it's a complete
				// line; if not, keep reading
				wstringstream inputs;
				while (true) {
					wstring line;
					getline(wcin, line);
					inputs << line << endl;
					if (lineChecker(inputs.str()))
						break;
					wcout << L"... ";
				}

				// run the input script
				wcout << eval(inputs.str()) << endl << endl;
			}

			return 0;
		}

		static BOOL ctrlHandler(DWORD fdwCtrlType) {
			if (fdwCtrlType == CTRL_C_EVENT) {
				repl::s_done = true;
				return TRUE;
			}

			return FALSE;
		}
	};
};