/*
 * This source file is part of MyGUI. For the latest info, see http://mygui.info/
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#ifndef MYGUI_RESIZING_POLICY_H_
#define MYGUI_RESIZING_POLICY_H_

#include "MyGUI_Prerequest.h"

namespace MyGUI
{

	struct MYGUI_EXPORT ResizingPolicy
	{
		enum Enum
		{
			Auto,
			Fixed,
			Fill,
			MAX
		};

		ResizingPolicy(Enum _value = MAX) :
			mValue(_value)
		{
		}

		static ResizingPolicy parse(std::string_view _value)
		{
			ResizingPolicy type;
			int value = 0;
			while (true)
			{
				std::string_view name = type.getValueName(value);
				if (name.empty() || name == _value)
					break;
				value++;
			}
			type.mValue = Enum(value);
			return type;
		}

		friend bool operator==(ResizingPolicy const& a, ResizingPolicy const& b)
		{
			return a.mValue == b.mValue;
		}

		friend bool operator!=(ResizingPolicy const& a, ResizingPolicy const& b)
		{
			return a.mValue != b.mValue;
		}

		friend std::ostream& operator<<(std::ostream& _stream, const ResizingPolicy& _value)
		{
			_stream << _value.getValueName(_value.mValue);
			return _stream;
		}

		friend std::istream& operator>>(std::istream& _stream, ResizingPolicy& _value)
		{
			std::string value;
			_stream >> value;
			_value = parse(value);
			return _stream;
		}

		std::string_view print() const
		{
			return getValueName(mValue);
		}

		int getValue() const
		{
			return mValue;
		}

	private:
		std::string_view getValueName(int _index) const
		{
			if (_index < 0 || _index >= MAX)
				return {};
			static const std::string_view values[MAX] = {"Auto", "Fixed", "Fill"};
			return values[_index];
		}

	private:
		Enum mValue;
	};

} // namespace MyGUI

#endif // MYGUI_RESIZING_POLICY_H_
