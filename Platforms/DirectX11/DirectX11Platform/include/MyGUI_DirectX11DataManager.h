/*!
	@file
	@author		Ustinov Igor aka Igor', DadyaIgor
	@date		09/2011
*/
#ifndef MYGUI_DIRECTX11_DATA_MANAGER_H_
#define MYGUI_DIRECTX11_DATA_MANAGER_H_

#include "MyGUI_Prerequest.h"
#include "MyGUI_DataManager.h"

namespace MyGUI
{

	class DirectX11DataManager : public DataManager
	{
	public:
		DirectX11DataManager();

		void initialise();
		void shutdown();

		static DirectX11DataManager& getInstance()
		{
			return *getInstancePtr();
		}
		static DirectX11DataManager* getInstancePtr()
		{
			return static_cast<DirectX11DataManager*>(DataManager::getInstancePtr());
		}

		/** @see DataManager::getData(const std::string& _name) */
		virtual IDataStream* getData(const std::string& _name) const;

		/** @see DataManager::freeData */
		virtual void freeData(IDataStream* _data);

		/** @see DataManager::isDataExist(const std::string& _name) */
		virtual bool isDataExist(const std::string& _name) const;

		/** @see DataManager::getDataListNames(const std::string& _pattern) */
		virtual const VectorString& getDataListNames(const std::string& _pattern) const;

		/** @see DataManager::getDataPath(const std::string& _name) */
		std::string getDataPath(const std::string& _name) const override;

		/*internal:*/
		void addResourceLocation(const std::string& _name, bool _recursive);

	private:
		struct ArhivInfo
		{
			std::wstring name;
			bool recursive;
		};
		using VectorArhivInfo = std::vector<ArhivInfo>;
		VectorArhivInfo mPaths;

		bool mIsInitialise;
	};

} // namespace MyGUI

#endif // MYGUI_DIRECTX11_DATA_MANAGER_H_
