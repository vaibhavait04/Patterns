

BST::Node::Node( int v ) { value = v;  left = rite = 0; }

void BST::add( Node** n, int v ) {
   if ( ! *n)                 { *n = new Node( v );  size++; }
   else if (v <= (*n)->value) add( &((*n)->left), v );
   else                       add( &((*n)->rite), v );
}

void BST::add( int v ) { add( &root, v ); }
void BST::traverse() { traverse( root ); }

void BST::traverse( Node* n ) {
   if (n->left) traverse( n->left );
   cout << n->value << ' ';
   if (n->rite) traverse( n->rite );
}

Iterator* BST::createIterator() const { return new Iterator( this ); }





