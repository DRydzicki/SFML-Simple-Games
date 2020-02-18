#pragma once

#include<string>
#include<unordered_map>

template<typename Resource>
class ResourceManager
{
private:
	const std::string folder;
	const std::string extension;
	std::unordered_map<std::string, Resource> resources;



public:
	ResourceManager(std::string filePath, std::string fileType): 
		folder("Resources/" + filePath + "/"), 
		extension("." + fileType)
	{}

	Resource& get(std::string name) {
		if (!ifExist(name))
			add(name);
		return resources.at(name);
	}

	bool ifExist(std::string name) const{
		if (resources.find(name) != resources.end())
			return true;
		return false;
	}

	void add(std::string name) {
		Resource resource;
		if (!resource.loadFromFile(folder + name + extension)) {
			Resource temp;
			temp.loadFromFile(folder + "noResource" + extension);
			resources.emplace(name, temp);
		}
		else 
			resources.emplace(name, resource);
	}
};



