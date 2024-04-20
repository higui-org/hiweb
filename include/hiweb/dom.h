#ifndef HiWEB_DOM_H
#define HiWEB_DOM_H

#include <string>
#include <memory>
#include <list>
#include <vector>
#include <unordered_map>

#include "hiweb/document.h"

namespace hi::web
{
    /**
     * @class Tag
     * @brief Represents a tag within a parsed document structure.
     *
     * This class encapsulates the properties of a tag, including its name, ID, classes, children, and attributes,
     * using a single string `data` for storing all textual values. It allows for efficient memory use by storing all
     * tag-related text in one contiguous block of memory.
     */
    class Tag
    {
    public:
        using Pointer = std::shared_ptr<Tag>; ///< Shared pointer to Tag
        using WeakPointer = std::weak_ptr<Tag>; ///< Weak pointer to Tag for parent-child relationship without creating circular references

        /**
        * @brief Constructor for the Tag class.
        * @param name The name of the tag.
        * @param text The text content of the tag.
        * @param id The ID of the tag.
        * @param classes The classes of the tag.
        * @param attributes The attributes of the tag.
        * @return A new Tag object.
        * @details initializes a new Tag object with the given name, text, ID, classes, and attributes.
        */
        explicit Tag (std::string name,
            std::string text = "",
            std::string id = "",
            std::vector<std::string> classes = {},
            std::unordered_map <std::string, std::string> attributes = {});

        /**
        * @brief Sets the name of the tag.
        * @param name The name of the tag.
        * @details sets the name of the tag by updating the `data` string with the new name.
        */
        void setName(const std::string& name) noexcept;

        /**
        * @brief Sets the ID of the tag.
        * @param id The ID of the tag.
        * @details sets the ID of the tag by updating the `data` string with the new ID.
        */
        void setId(const std::string& id) noexcept;

        /**
        * @brief Adds a class to the tag.
        * @param class_name The class to add.
        * @details adds a class to the tag by updating the `data` string with the new class name.
        */
        void addClass(const std::string& class_name) noexcept;

        /**
        * @brief Removes a class from the tag.
        * @param class_name The class to remove.
        * @details removes a class from the tag by updating the `data` string to remove the class name.
        */
        void removeClass(const std::string& class_name) noexcept;

        /**
         * @brief Adds a child tag to this tag.
         * @param child The child tag to add.
         * @details adds a child tag to the current tag by appending it to the list of children.
         */
        void addChild(Pointer child) noexcept;

        /**
        * @brief Sets an attribute for the tag.
        * @param key The key of the attribute.
        * @param value The value of the attribute.
        * @details sets an attribute for the tag by updating the `data` string with the new attribute.
        */
        void setAttribute(const std::string& key, const std::string& value) noexcept;

        /**
        * @brief Removes an attribute from the tag.
        * @param key The key of the attribute to remove.
        * @details removes an attribute from the tag by updating the `data` string to remove the attribute.
        */
        void removeAttribute(const std::string& key) noexcept;




        /**
        * @brief Gets the name of the tag.
        */
        std::string getName() const noexcept;


        /**
        * @brief Gets the ID of the tag.
        */
        std::string getId() const noexcept;

        /**
        * @brief Gets the classes of the tag.
        * @return A vector of class names.
        */
        std::vector<std::string> getClasses() const noexcept;

        /**
        * @brief Gets the attributes of the tag.
        * @return A map of attribute key-value pairs.
        */
        std::unordered_map<std::string, std::string> getAttributes() const noexcept;

        /**
        * @brief Gets the children of the tag.
        * @return A vector of child tags.
        */
        std::vector<Pointer> getChildren() const noexcept;

        /**
        * @brief Gets the text content of the tag.
        */
        std::string getText() const noexcept;

        /**
        * @brief Gets the inner markup of the tag.
        */
        std::string innerMarkup() const noexcept;

        void UpdateIndexes(
            size_t str_length,
            bool for_name = false, 
            bool for_id = false, 
            bool for_classes = false,
            bool for_attributes = false, 
            bool for_text = false) noexcept;

    private:
        std::unordered_map<std::string, StringIndex> attribute_indexes; ///< Indexes for attributes (key and value).
        StringIndex name_index, id_index, text_index; ///< Indexes for name, ID and text.
        std::list<StringIndex> class_indexes; ///< Indexes for classes.

        std::vector<Pointer> children; ///< Child tags.
        WeakPointer parent; ///< Parent tag.

        /**
         * @brief Sets the index range for the tag's name within `data`.
         * @param start The start index of the tag's name.
         * @param length The length of the tag's name.
         * @details sets the index range for the tag's name within the `data` string.
         */
        void setNameIndex(unsigned int start, unsigned int length) noexcept;

        /**
         * @brief Sets the index range for the tag's ID within `data`.
         * @param start The start index of the tag's ID.
         * @param length The length of the tag's ID.
         * @details sets the index range for the tag's ID within the `data` string.
         */
        void setIdIndex(unsigned int start, unsigned int length) noexcept;

        /**
         * @brief Sets the index range for the tag's classes within `data`.
         * @param start The start index of the class list.
         * @param length The length of the class list.
         */
        void setClassIndex(unsigned int start, unsigned int length) noexcept;

        /**
         * @brief Sets the index range for an attribute within `data`.
         * @param key The attribute key.
         * @param start The start index of the attribute's value.
         * @param length The length of the attribute's value.
         * @details sets the index range for an attribute's value within the `data` string.
         */
        void setAttributeIndex(const std::string& key, unsigned int start, unsigned int length) noexcept;

        /**
         * @brief Sets the index range for the tag's text within `data`.
         * @param start The start index of the text.
         * @param length The length of the text.
         */
        void setTextIndex(unsigned int start, unsigned int length) noexcept;

        /**
        * @brief Update and insert the index of the tag.
        * @param index The index to update.
        * @param str The substring to insert.
        * @details Indexes must be updated to reflect the new positions of the tag's components within the `data` string.
        */
        void UpdateStringIndex(StringIndex& index, const std::string& str) noexcept;
    };


    /**
     * @class DOM
     * @brief Manages a tree of Tag objects.
     *
     * This class provides functionality to manipulate and navigate a tree of Tag objects,
     * representing the structured hierarchy of a parsed document. It supports operations
     * such as setting the root tag, printing the structure of the tag tree, and accessing
     * the root tag of the document.
     */
    class DOM
    {
    public:
        /**
         * @brief Sets the root tag of the document.
         * @param root The root tag to be set for the document.
         */
        void setRoot(Tag::Pointer root) noexcept { this->root = root; }

        /**
         * @brief Retrieves the root tag of the document.
         * @return The root tag of the document.
         */
        Tag::Pointer getRoot() const noexcept { return root; };

    private:
        mutable Tag::Pointer root; ///< The root of the tag tree, mutable to allow modification in const methods.
    };
} // namespace hi::web

#endif // HiWEB_DOM_H