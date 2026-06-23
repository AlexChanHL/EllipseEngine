
#include "LayerStack.hpp"

namespace Ellipse {
 void pushLayerToStack(LayerStack& stack, std::shared_ptr<ILayer> layer) {
    LayerStack::Page* nextPage = new LayerStack::Page();
 
    stack.current->m_header.next = nextPage;
 
    stack.current->m_header.next->m_header.prev = stack.current;
 
    stack.current = stack.current->m_header.next;
    stack.current->m_layer = std::move(layer);
 }
 
 void updateLayerStack(LayerStack& stack, float dt) {
    LayerStack::Page* ptr = stack.first;
    while(ptr) {
     if(!ptr->m_layer->isHidden()) {
      ptr->m_layer->onUpdate(dt);
     }
 
     ptr = ptr->m_header.next;
    }
 }
 
 void updateLayerEvents(LayerStack& stack, Event& event) {
  LayerStack::Page* ptr = end(stack);
  while(ptr) {
   if(!ptr->m_layer->isHidden()) {
    ptr->m_layer->onEvent(event);
   }
   ptr = ptr->m_header.prev;
  }
 }
 
 LayerStack::Page* begin(LayerStack& stack) {
    return stack.first; 
 }
 
 LayerStack::Page* end(LayerStack& stack) {
    LayerStack::Page* ptr = stack.first;
    while(ptr->m_header.next) {
     ptr = ptr->m_header.next;
    }
    return ptr;
 }
 
}

