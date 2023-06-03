/*
 * This source file is part of MyGUI. For the latest info, see http://mygui.info/
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#ifndef MYGUI_LOG_MANAGER_H_
#define MYGUI_LOG_MANAGER_H_

#include "MyGUI_Prerequest.h"
#include "MyGUI_LogStream.h"
#include "MyGUI_LogSource.h"
#include "MyGUI_Diagnostic.h"
#include <memory>
#include <vector>

namespace MyGUI
{

#define MYGUI_LOGGING(section, level, text) \
		MyGUI::LogManager::getInstance().log(section, MyGUI::LogLevel::level, MyGUI::LogStream() << text << MyGUI::LogStream::End(), __FILE__, __LINE__)

	class ConsoleLogListener;
	class FileLogListener;
	class LevelLogFilter;

	class MYGUI_EXPORT LogManager
	{
	public:
		LogManager();
		~LogManager();

		static LogManager& getInstance();
		static LogManager* getInstancePtr();

		/** Call LogSource::flush() for all log sources. */
		void flush();
		/** Call LogSource::log for all log sources. */
		void log(std::string_view _section, LogLevel _level, std::string_view _message, std::string_view _file, int _line);

		/** Create default LevelLogFilter, FileLogListener and ConsoleLogListener. */
		void createDefaultSource(std::string_view _logname);

		/** Enable or disable default ConsoleLogListener that writes log into std::cout.\n
			Enabled (true) by default.
		*/
		void setSTDOutputEnabled(bool _value);
		/** Is disable ConsoleLogListener enabled. */
		bool getSTDOutputEnabled() const;

		/** Set default LevelLogFilter level. */
		void setLoggingLevel(LogLevel _value);
		/** Get default LevelLogFilter level. */
		LogLevel getLoggingLevel() const;

		/** Add log source. */
		void addLogSource(LogSource* _source);

	private:
		void close();

	private:
		static LogManager* msInstance;

		using VectorLogSource = std::vector<LogSource*>;
		VectorLogSource mSources;

		std::unique_ptr<ConsoleLogListener> mConsole;
		std::unique_ptr<FileLogListener> mFile;
		std::unique_ptr<LevelLogFilter> mFilter;
		std::unique_ptr<LogSource> mDefaultSource;

		LogLevel mLevel{LogLevel::Info};
		bool mConsoleEnable{true};
	};

} // namespace MyGUI

#endif // MYGUI_LOG_MANAGER_H_
