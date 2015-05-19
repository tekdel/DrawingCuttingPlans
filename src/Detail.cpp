#include "../stdafx.h"
#include "../headers/Detail.h"

template<typename T>
Detail<T>& Detail<T>::Add(Drawable<T>* element){
	this->_elements.push_back(element);
	return *this;
};

template<typename T>
Detail<T>& Detail<T>::Add(std::vector<Drawable<T>*> elements){
	this->_elements.insert(this->_elements.end(), elements.begin(), elements.end());
	return *this;
}

template<typename T>
void Detail<T>::Draw(cimg_library::CImg<T> img){
	for (std::vector<Drawable<T>*>::iterator it = this->_elements.begin(); it != this->_elements.end(); ++it)
	{
		(*it)->Draw(img);
	}
	this->_elements.clear();
};


/*void Draw(cimg_library::CImg<T> img){
for (std::vector<Drawable<T>>::iterator it = this->_elements.begin(); it != this->_elements.end(); ++it)
{
it->Draw(img);
}
this->_elements.clear();
//return *this;
}*/
/*
template<typename T>
void Detail<T>::Draw(cimg_library::CImg<T> img){
for (std::vector<Drawable<T>>::iterator it = this->_elements.begin(); it != this->_elements.end(); ++it)
{
it->Draw(img);
}
this->_elements.clear();
}*/