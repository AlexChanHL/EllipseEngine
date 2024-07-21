#pragma once

#include "Layer.hpp"

namespace Ellipse
{

struct LayerStack
{
    public:
     // struct Page;
      struct Page
      {
         public:
        struct Header
      {
         public:
          Page* next = nullptr;
          Page* prev = nullptr;
      };
        public:
         Header m_header;
         std::shared_ptr<Layer> m_layer = nullptr;
      };

    public:
     LayerStack()
      {
     first = new Page(Page::Header{nullptr, nullptr}, std::make_shared<PlaceHolderLayer>());
     current = first;
      }
     ~LayerStack()
      {
      Page* ptr = first;
      Page* p = first;

         while(ptr)
          {
            ptr = ptr->m_header.next;
             delete p;
            p = ptr;
          }

      }
     
    public:
     Page* first = nullptr;
     Page* current = nullptr;
};

   LayerStack::Page* begin(LayerStack& stack);
   LayerStack::Page* end(LayerStack& stack);

   void debug(LayerStack::Page* ptr);

void pushLayerToStack(LayerStack& stack, std::shared_ptr<Layer> layer);

void updateLayerStack(LayerStack& stack);

void updateLayerEvents(LayerStack& stack, Event& event);

// hideLayer

}
