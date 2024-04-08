#ifndef HiWEB_DOM_H
#define HiWEB_DOM_H

#include <string>
#include <memory>
#include <list>
#include <unordered_map>

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
         * @struct StringIndex
         * @brief Represents the start and end indexes of a substring within the `data` string.
         *
         * This structure is used to reference various textual components of the tag such as name, ID, classes, and attributes
         * without storing multiple copies of the same strings.
         */
        struct StringIndex
        {
            unsigned int start; ///< Starting index of the substring
            unsigned int end;   ///< Ending index (exclusive) of the substring
        };

        explicit Tag (std::string name,
            std::string text = "",
            std::string id = "",
            std::vector<std::string> classes = {},
            std::unordered_map <std::string, std::string> attributes = {});

        /**
         * @brief Sets the index range for the tag's name within `data`.
         * @param start The start index of the tag's name.
         * @param length The length of the tag's name.
         */
        void setNameIndex(unsigned int start, unsigned int length) noexcept;

        /**
         * @brief Sets the index range for the tag's ID within `data`.
         * @param start The start index of the tag's ID.
         * @param length The length of the tag's ID.
         */
        void setIdIndex(unsigned int start, unsigned int length) noexcept;

        /**
         * @brief Sets the index range for the tag's classes within `data`.
         * @param start The start index of the class list.
         * @param length The length of the class list.
         */
        void setClassIndex(unsigned int start, unsigned int length) noexcept;

        /**
         * @brief Adds a child tag to this tag.
         * @param child The child tag to add.
         */
        void addChild(Pointer child) noexcept;

        /**
         * @brief Sets the index range for an attribute within `data`.
         * @param key The attribute key.
         * @param start The start index of the attribute's value.
         * @param length The length of the attribute's value.
         */
        void setAttributeIndex(const std::string& key, unsigned int start, unsigned int length) noexcept;

        /**
         * @brief Sets the index range for the tag's text within `data`.
         * @param start The start index of the text.
         * @param length The length of the text.
         */
        void setTextIndex(unsigned int start, unsigned int length) noexcept;

        // Getters
        std::string getName() const noexcept;
        std::string getId() const noexcept;
        std::vector<std::string> getClasses() const noexcept;
        std::unordered_map<std::string, std::string> getAttributes() const noexcept;
        std::vector<Pointer> getChildren() const noexcept;
        std::string getText() const noexcept;
        std::string innerMarkup() const noexcept;

    private:
        std::string data; ///< Stores all text related to the tag (name, ID, classes, attributes, and text content).
        StringIndex name_index, id_index, text_index; ///< Indexes for name, ID and text.
        std::list<StringIndex> class_indexes; ///< Indexes for classes.
        std::unordered_map<std::string, StringIndex> attribute_indexes; ///< Indexes for attributes (key and value).
        std::vector<Pointer> children; ///< Child tags.
        WeakPointer parent; ///< Parent tag.
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