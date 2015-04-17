// Purpose.  Chain of Responsibility and Command demo
// 
// Chain of Responsibility -
// 1. Base class maintains a "next" pointer
// 2. Each "node" object evaluates each request
// 3. Node object may pass on a request to the
//    next node
// 4. Client "launches and leaves" each request
//
// Command -
// 5. Base class specifies an "execute" method
// 6. Derived classes call a method on an object

import java.awt.*;

public class CommandChainDemo {

   interface Command {
      public void execute( Component c );                           //// 5 \\\\
   }
   static class Back implements Command {
      private Color color;
      public Back( Color c )             { color = c; }
      public void execute( Component c ) { c.setBackground( color ); }  // 6 \\
   }
   static class Fore implements Command {
      private Color color;
      public Fore( Color c )             { color = c; }
      public void execute( Component c ) { c.setForeground( color ); }
   }

   static class ChainNode extends Button {
      private ChainNode next;                                       //// 1 \\\\

      public ChainNode( String name, ChainNode nx ) {
         super( name );
         setFont( new Font( "SansSerif", Font.BOLD, 30 ) );
         next = nx;
      }
      public void process( Command cmd ) {
         cmd.execute( this );                                       //// 2 \\\\
         if (next != null) next.process( cmd );                     //// 3 \\\\
   }  }

   public static ChainNode createChain( Frame f ) {
      ChainNode last   = new ChainNode( "third",  null );
      ChainNode middle = new ChainNode( "second", last );
      ChainNode first  = new ChainNode( "first",  middle );
      f.add( first );  f.add( middle );  f.add( last );
      return first;
   }

   public static void main( String[] args ) {
      Frame f = new Frame( "ChainCommandDemo" );
      f.setLayout( new FlowLayout() );
      ChainNode root = createChain( f );
      f.pack();
      f.setVisible( true );

      Command[] cmds = { new Back( Color.cyan ),   new Fore( Color.blue),
                         new Back( Color.yellow ), new Fore( Color.red)   };
      for (int i=0; i < cmds.length; i++) {
         Read.aString();
         root.process( cmds[i] );                                   //// 4 \\\\

} 
} 
}


