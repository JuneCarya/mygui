/*!
	@file
	@author		Albert Semenov
	@date		11/2007
	@module
*/
/*
	This file is part of MyGUI.
	
	MyGUI is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	
	MyGUI is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.
	
	You should have received a copy of the GNU Lesser General Public License
	along with MyGUI.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "MyGUI_Precompiled.h"
#include "MyGUI_SubWidgetManager.h"
#include "MyGUI_FactoryManager.h"
#include "MyGUI_CommonStateInfo.h"

namespace MyGUI
{

	MYGUI_INSTANCE_IMPLEMENT(SubWidgetManager);

	void SubWidgetManager::initialise()
	{
		MYGUI_ASSERT(false == mIsInitialise, INSTANCE_TYPE_NAME << " initialised twice");
		MYGUI_LOG(Info, "* Initialise: " << INSTANCE_TYPE_NAME);

		mFactorySubSkin = new SubWidgetFactory<SubSkin>();
		mFactoryMainSkin = new SubWidgetFactory<MainSkin>();
		mFactoryRotatingSkin = new SubWidgetFactory<RotatingSkin>();
		mFactorySimpleText = new SubWidgetFactory<SimpleText>();
		mFactoryEditText = new SubWidgetFactory<EditText>();
		mFactoryRawRect = new SubWidgetFactory<RawRect>();
		mFactoryTileRect = new SubWidgetFactory<TileRect>();

		registerFactory(mFactorySubSkin);
		registerFactory(mFactoryMainSkin);
		registerFactory(mFactoryRotatingSkin);
		registerFactory(mFactorySimpleText);
		registerFactory(mFactoryEditText);
		registerFactory(mFactoryRawRect);
		registerFactory(mFactoryTileRect);

		FactoryManager& factory = FactoryManager::getInstance();

		factory.registryFactory<SubSkinStateInfo>("SubWidgetState", "SubSkin");
		factory.registryFactory<SubSkinStateInfo>("SubWidgetState", "MainSkin");
		factory.registryFactory<SubSkinStateInfo>("SubWidgetState", "RotatingSkin");
		factory.registryFactory<SubSkinStateInfo>("SubWidgetState", "RawRect");
		factory.registryFactory<SubSkinStateInfo>("SubWidgetState", "TileRect");
		factory.registryFactory<EditTextStateInfo>("SubWidgetState", "EditText");
		factory.registryFactory<EditTextStateInfo>("SubWidgetState", "SimpleText");

		MYGUI_LOG(Info, INSTANCE_TYPE_NAME << " successfully initialized");
		mIsInitialise = true;
	}

	void SubWidgetManager::shutdown()
	{
		if (false == mIsInitialise) return;
		MYGUI_LOG(Info, "* Shutdown: " << INSTANCE_TYPE_NAME);

		mFactoryList.clear();

		delete mFactorySubSkin;
		delete mFactoryMainSkin;
		delete mFactoryRotatingSkin;
		delete mFactorySimpleText;
		delete mFactoryEditText;
		delete mFactoryRawRect;
		delete mFactoryTileRect;

		FactoryManager& factory = FactoryManager::getInstance();

		factory.unregistryFactory("SubWidgetState", "SubSkin");
		factory.unregistryFactory("SubWidgetState", "MainSkin");
		factory.unregistryFactory("SubWidgetState", "RotatingSkin");
		factory.unregistryFactory("SubWidgetState", "RawRect");
		factory.unregistryFactory("SubWidgetState", "TileRect");
		factory.unregistryFactory("SubWidgetState", "EditText");
		factory.unregistryFactory("SubWidgetState", "SimpleText");

		MYGUI_LOG(Info, INSTANCE_TYPE_NAME << " successfully shutdown");
		mIsInitialise = false;
	}

	ISubWidget * SubWidgetManager::createSubWidget(const SubWidgetInfo &_info, ICroppedRectangle * _parent)
	{
		for (ListFactory::iterator factory = mFactoryList.begin(); factory != mFactoryList.end(); factory++)
		{
			if ((*factory)->getTypeName() == _info.type) return (*factory)->createSubWidget(_info, _parent);
		}
		MYGUI_EXCEPT("factory type '" << _info.type << "' not found.");
		return nullptr;
	}

	/*StateInfo * SubWidgetManager::getStateData(const std::string& _factory, xml::ElementPtr _node, xml::ElementPtr _root, Version _version)
	{
		for (ListFactory::iterator factory = mFactoryList.begin(); factory != mFactoryList.end(); factory++)
		{
			if ((*factory)->getTypeName() == _factory) return (*factory)->createData(_node, _root, _version);
		}
		MYGUI_LOG(Error, "factory type '" << _factory << "' not found. (SubWidgetManager::getStateData)");
		return nullptr;
	}*/

} // namespace MyGUI
