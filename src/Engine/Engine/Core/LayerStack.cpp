
#include "LayerStack.hpp"

namespace Ellipse {
 void LayerStack::push(std::shared_ptr<ILayer> layer) {
    LayerStack::Page* nextPage = new LayerStack::Page();

    m_current->m_header.next = nextPage;

    m_current->m_header.next->m_header.prev = m_current;

    m_current = m_current->m_header.next;
    m_current->m_layer = std::move(layer);
  // m_layers.push_back(layer);
 }
 
 void LayerStack::update(float dt) {
    LayerStack::Page* ptr = m_first;
    while(ptr) {
     if(!ptr->m_layer->isHidden()) {
      ptr->m_layer->onUpdate(dt);
     }

     ptr = ptr->m_header.next;
    }
  //
  // for(auto a : m_layers) {
  //  a->onUpdate(dt);
  // }
 }
 
 void LayerStack::updateEvents(Event& e) {
  LayerStack::Page* ptr = end();
  while(ptr) {
   if(!ptr->m_layer->isHidden()) {
    ptr->m_layer->onEvent(e);
   }
   ptr = ptr->m_header.prev;
  }
  //
  // for(i64_t i=i64_t(m_layers.size()) - 1; i>=0; i--) {
  //  if(!m_layers[u64_t(i)]->isHidden()) {
  //   m_layers[u64_t(i)]->onEvent(e);
  //  }
  // }
 }  

}

