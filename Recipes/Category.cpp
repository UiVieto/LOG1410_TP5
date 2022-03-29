#include <string>

#include "Category.h"
#include "AbsProduct.h"

int Category::m_indent = 0;

Category::Category(std::string name)
	: AbsCatalogComponent(name)
{
}

Category::Category(const Category& mdd)
	: AbsCatalogComponent(mdd.m_name)
{
	// � compl�ter pour copier tous les �l�ments du catalogue contenus dans la cat�gorie
	for (auto&& product : mdd.m_products) {
		this->addCatalogComponent(*product);
	}
}

Category* Category::clone(void) const
{
	// � compl�ter pour construire un nouvel objet Category en appelant le constructeur de copie
	return new Category(*this);
}

AbsCatalogComponent& Category::addCatalogComponent(const AbsCatalogComponent& member)
{
	// � compl�ter pour construire par clonage une copie de l'objet re�u en param�tre
	// et l'ins�rer dans le conteneur de produits. On retourne une r�f�rence � l'objet
	// qui vient d'�tre ins�r� dans le conteneur.
	m_products.push_back(CatalogComponentPtr(member.clone()));

	return *m_products.back();
}

CatalogComponentIterator Category::begin()
{
	return m_products.begin();
}

CatalogComponentIterator_const Category::cbegin() const
{
	return m_products.cbegin();
}

CatalogComponentIterator_const Category::cend() const
{
	return m_products.cend();
}

CatalogComponentIterator Category::end()
{
	return m_products.end();
}

void Category::deleteCatalogComponent(CatalogComponentIterator_const child)
{
	// � compl�ter pour �liminer de la cat�gorie l'�l�ment auquel r�f�re l'it�rateur
	m_products.erase(child);
}

void Category::deleteAllComponents(void)
{
	// � compl�ter pour �liminer tous les �l�ments de la cat�gorie
	while (m_products.size() > 0) {
		m_products.pop_back();
	}
}

const AbsProduct* Category::findProduct(std::string productName) const
{
	// � compl�ter pour it�rer sur les �l�ments contenus dans la cat�gorie � la recherche d'un produit
	// portant le nom re�u en argument. Si aucun produit n'est trouv� on retourne nullptr
	const AbsProduct* foundProduct = nullptr;
	const Category* foundCategory = nullptr;
	// � compl�ter
	for (auto&& product : m_products) {
		foundProduct = dynamic_cast<const AbsProduct*>(product.get());
		if (foundProduct != nullptr) {
			if (foundProduct->getName() == productName)
				return foundProduct;
		}
		else {
			foundCategory = dynamic_cast<const Category*>(product.get());
			if (foundCategory != nullptr) {
				return foundCategory->findProduct(productName);
			}
		}
	}
}

std::ostream& Category::printToStream(std::ostream& o) const
{
	// � compl�ter pour imprimer sur un stream une cat�gorie et ses produits
	o << "Category: " << m_name << std::endl;
	std::list<CatalogComponentPtr>::const_iterator it;
	for (it = m_products.cbegin(); it != m_products.cend(); it++)
	{
		o << "\t" << "Category: " << it->get()->getName() << std::endl;
		o << std::endl;
	}

	return o;
}

std::ostream& Category::indent(std::ostream& o) const
{
	for (int i = 0; i < m_indent; ++i)
		o << '\t';
	return o;
}