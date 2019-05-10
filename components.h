#ifndef COMPONENTS_H
#define COMPONENTS_H
#include <set>


class Components{
private:
    unsigned long int id;
    std::set<unsigned long int> elements;
public:
    Components();
    Components(unsigned long int id);
    std::set<unsigned long int> GetElements();
    void Union(Components c);
    unsigned long int GetId() const;
    bool operator = (const Components & c) const;
    bool operator = (const unsigned long int & id) const;
    bool operator < ( const Components & c) const;
    bool operator < ( const unsigned long int & id) const;
};

struct find_by_id {
    find_by_id(const unsigned long int & id) : id(id) {}
    bool operator()(Components & c) {
        return c.GetId() == id;
    }
private:
    unsigned long int id;
};

#endif // COMPONENTS_H
