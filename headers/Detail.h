#include "Drawable.h";
#include <vector>;

#pragma once
template<typename T>
class Detail : public Drawable<T>
{
private:
	std::vector<Drawable<T>*> _elements;
public:
	Detail<T>& Add(Drawable<T>* element);
	Detail<T>& Add(std::vector<Drawable<T>*> elements);
	virtual void Draw(cimg_library::CImg<T> img);
};