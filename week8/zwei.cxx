//
// Created by thomasf on 17.03.2020.
//

#include <fstream>
#include <vector>
#include <fstream>


struct Value
{
    const std::string key;
    std::string value;

    Value * next;
    Value * linked_next;
    Value * linked_prev;

    explicit
    Value(std::string key, std::string value, Value * prev, Value * next) :
            next(nullptr), key(key), value(value), linked_prev(prev),
            linked_next(next) {}
};

struct LinkedHashMap
{
//    const unsigned int MOD = 200001;
    const unsigned int MOD = 96557;
    std::vector<Value *> table;

    Value * header;

    Value * linked_next;
    Value * linked_prev;

    LinkedHashMap()
    {
        linked_next = nullptr;
        linked_prev = nullptr;
        header = new Value("<none>", "<none>", nullptr, nullptr);
        header->linked_prev = header;
        header->linked_next = header;
        table.resize(MOD);
    }

    int hash(const std::string& s)
    {
        int multiplier = 263;
        int prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = s.size() - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return static_cast<int> (hash);
    }


    void add(const std::string &key, const std::string &value)
    {
        Value * x = get_value(key);
        if (x != nullptr)
        {
            x->value = value;
            return;
        }
        int h = hash(key);
        Value * node = new Value(key, value, header->linked_prev, header);
        header->linked_prev->linked_next = node;
        node->next = table[h % MOD];
        table[h % MOD] = node;
        header->linked_prev = node;
    }

    std::string next(const std::string &key)
    {
        Value * node = get_value(key);
        return node == nullptr ? "<none>" : node->linked_next->value;
    }

    std::string prev(const std::string &key)
    {
        Value * node = get_value(key);
        return node == nullptr ? "<none>" : node->linked_prev->value;
    }

    Value * get_value(const std::string &key)
    {
        Value * node = table[hash(key) % MOD];
        while (node != nullptr)
        {
            if (node->key == key)
            {
                return node;
            }
            node = node->next;
        }
        return nullptr;
    }

    std::string get(const std::string &key)
    {
        Value * node = get_value(key);
        return node == nullptr ? "<none>" : node->value;
    }

    void remove(const std::string &key)
    {
        int h = hash(key);
        Value * node = table[h % MOD];
        Value * prev_node = nullptr;
        while (node != nullptr)
        {
            if (node->key == key)
            {
                node->linked_next->linked_prev = node->linked_prev;
                node->linked_prev->linked_next = node->linked_next;
                if (prev_node == nullptr)
                {
                    table[h % MOD] = node->next;
                }
                else
                {
                    prev_node->next = node->next;
                    node->next = nullptr;
                }
                return;
            }
            prev_node = node;
            node = node->next;
        }
    }
};


int main()
{
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");
    LinkedHashMap linkedHashMap;
    uint64_t n;
    input >> n;
    while (!input.eof())
    {
        std::string operation;
        std::string key;
        input >> operation >> key;
        if (operation == "put")
        {
            std::string value;
            input >> value;
            linkedHashMap.add(key, value);
        }
        if (operation == "delete")
        {
            linkedHashMap.remove(key);
        }
        if (operation == "get")
        {
            output << linkedHashMap.get(key) << "\n";
        }
        if (operation == "prev")
        {
            output << linkedHashMap.prev(key) << "\n";
        }
        if (operation == "next")
        {
            output << linkedHashMap.next(key) << "\n";
        }
    }
    return 0;
}