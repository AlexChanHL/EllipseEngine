#pragma once

#include "Layer.hpp"


namespace Ellipse {
 struct LayerStack {
     public:
       struct Page {
          public:
         struct Header {
          public:
           Page* next = nullptr;
           Page* prev = nullptr;
       };
         public:
          Header m_header;
          SharedPtr<ILayer> m_layer = nullptr;
       };
 
     public:
      LayerStack() {
       m_first = new Page(Page::Header{nullptr, nullptr}, Layer::createDefaultLayer());
       m_current = m_first;
      }
      ~LayerStack() {
       Page* ptr = m_first;
       Page* p = m_first;
       while(ptr) {
        ptr = ptr->m_header.next;
        delete p;
        p = ptr;
       }
      }
      void push(SharedPtr<ILayer> layer);
      void updateEvents(Event& event);
      void update(float dt);

      LayerStack::Page* begin() {
         return m_first; 
      }
      
      LayerStack::Page* end() {
         LayerStack::Page* ptr = m_first;
         while(ptr->m_header.next) {
          ptr = ptr->m_header.next;
         }
         return ptr;
      }
  
     public:
      Page* m_first = nullptr;
      Page* m_current = nullptr;

     private:
      Vector<SharedPtr<ILayer>> m_layers;
 };

}

