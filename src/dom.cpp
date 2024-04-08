#include "hiweb/dom.h"

namespace hi::web
{
    /*
        class Tag
            |
            |
           \ /

*/
    Tag::Tag 
        (std::string name,
        std::string text,
        std::string id,
        std::vector<std::string> classes,
        std::unordered_map <std::string, std::string> attributes)
    {
        name_index = id_index = text_index = { 0,0 };

        unsigned int current_index = 1;
        // Tag starts
        data = "<" + name;
        name_index = { current_index, static_cast<uint32_t>(current_index + name.length()) };
        current_index += static_cast<uint32_t>(name.length()) + 1;

        // add ID
        if (!id.empty())
        {
            data += " id=\"" + id + "\"";
            id_index = { current_index + 4, static_cast<uint32_t>(current_index + 4 + id.length()) }; // +4 for " id="
            current_index += static_cast<uint32_t>(4 + id.length() + 2); // +2
        }

        // add classes
        if (!classes.empty()) 
        {
            data += " class=\"";
            current_index += 8; // for " class="

            for (const auto& cls : classes) 
            {
                class_indexes.push_back({ current_index, static_cast<uint32_t>(current_index + cls.length()) });
                current_index += static_cast<uint32_t>(cls.length()) + 1; // +1 for space
                data += cls + " ";
            }
            data.pop_back();
            data += "\"";
            current_index += 1;
        }

        // add attributes
        for (const auto& [key, value] : attributes) 
        {
            attribute_indexes[key] = { current_index + static_cast<uint32_t>(key.length() + 3), static_cast<uint32_t>(current_index + key.length() + 3 + value.length()) };
            current_index += static_cast<uint32_t>(key.length() + value.length() + 4); // +4 for " =" and quotes
            data += " " + key + "=\"" + value + "\"";
        }

        // add text
        data += ">" + text;
        text_index = { current_index, static_cast<uint32_t>(current_index + text.length()) };
        current_index += static_cast<uint32_t>(text.length());
        // and close tag
        data += "</" + name + ">";
    }

    void Tag::setNameIndex(unsigned int start, unsigned int length) noexcept 
    {
        name_index.start = start;
        name_index.end = start + length;
    }

    void Tag::setIdIndex(unsigned int start, unsigned int length) noexcept 
    {
        id_index.start = start;
        id_index.end = start + length;
    }

    void Tag::setClassIndex(unsigned int start, unsigned int length) noexcept 
    {
        uint32_t end = start + length;
        uint32_t class_start = start;
        for (uint32_t i = start; i <= end; ++i) 
        {
            if (data[i] == ' ' || i == end) 
            {
                class_indexes.push_back({ class_start, i });
                class_start = i + 1;
            }
        }
    }

    void Tag::addChild(Pointer child) noexcept 
    {
        children.push_back(child);
    }

    void Tag::setAttributeIndex(const std::string& key, unsigned int start, unsigned int length) noexcept 
    {
        attribute_indexes[key] = { start, start + length };
    }

    void Tag::setTextIndex(unsigned int start, unsigned int length) noexcept 
    {
        text_index.start = start;
        text_index.end = start + length;
    }

    std::string Tag::getName() const noexcept 
    {
        return data.substr(name_index.start, name_index.end - name_index.start);
    }


    std::string Tag::getId() const noexcept 
    {
        return data.substr(id_index.start, id_index.end - id_index.start);
    }

    std::vector<std::string> Tag::getClasses() const noexcept 
    {
        std::vector<std::string> classes;
        for (const auto& class_index : class_indexes) 
        {
            classes.push_back(data.substr(class_index.start, class_index.end - class_index.start));
        }
        return classes;
    }


    std::unordered_map<std::string, std::string> Tag::getAttributes() const noexcept 
    {
        std::unordered_map<std::string, std::string> attributes;
        for (const auto& [key, val_index] : attribute_indexes) 
        {
            attributes[key] = data.substr(val_index.start, val_index.end - val_index.start);
        }
        return attributes;
    }

    std::vector<Tag::Pointer> Tag::getChildren() const noexcept 
    {
        return children;
    }

    std::string Tag::getText() const noexcept 
    {
        return data.substr(text_index.start, text_index.end - text_index.start);
    }

    std::string Tag::innerMarkup() const noexcept
    {
        return data;
    }
    /*
                   / \
                    |
                    |
                class Tag
    */







}   // namespace hi::web

