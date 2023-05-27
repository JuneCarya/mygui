/*
 * This source file is part of MyGUI. For the latest info, see http://mygui.info/
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#ifndef MYGUI_CONTROLLER_MANAGER_H_
#define MYGUI_CONTROLLER_MANAGER_H_

#include "MyGUI_Prerequest.h"
#include "MyGUI_Singleton.h"
#include "MyGUI_ControllerItem.h"
#include "MyGUI_IUnlinkWidget.h"
#include "MyGUI_WidgetDefines.h"
#include "MyGUI_ActionController.h"

namespace MyGUI
{

	class MYGUI_EXPORT ControllerManager :
		public IUnlinkWidget
	{
		MYGUI_SINGLETON_DECLARATION(ControllerManager);
	public:
		ControllerManager();

		void initialise();
		void shutdown();

		/** Create controller.
			@param _type Controller type name. Should be on of internal controllers or registered by user.
		*/
		ControllerItem* createItem(std::string_view _type);

		/** Add controller over widget.
			If specified widget already have controller with same type previous controller removed.
			@param _widget to be controlled
			@param _item controller created through createItem(std::string_view _type)
			@note _item will be deleted automatically at end of controller lifetime
				(if not removed by removeItem(Widget* _widget) before)
		*/
		void addItem(Widget* _widget, ControllerItem* _item);

		/** Stop and remove all controllers over specified widget.
			@param _widget Pointer to widget for removing control from.
		*/
		void removeItem(Widget* _widget);

		const std::string& getCategoryName() const;

	private:
		void _unlinkWidget(Widget* _widget) override;
		void frameEntered(float _time);
		void clear();

	private:
		using PairControllerItem = std::pair<Widget*, ControllerItem*>;
		using ListControllerItem = std::list<PairControllerItem>;
		ListControllerItem mListItem;

		bool mIsInitialise{false};
		std::string mCategoryName;
	};

} // namespace MyGUI

#endif // MYGUI_CONTROLLER_MANAGER_H_
