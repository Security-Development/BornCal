

import java.io.*;
import java.net.*;

class BonCalClientAPI  {

    private int MaxBuffer = 512;

    public BonCalClientAPI(String host = "127.0.0.1", int port = 9999) {
        Socket client = new Socket();
        SocketAddress address = new SocketAddress(host, port);

        client.connect(address);
        System.out.println("[+] Successful Socket Connection!!");

        try{
            System.out.println("[+] Recive Message : "+GetReciveMessage(client));
            client.close();
        }catch(Exception error) {
            error.printStackTrace();
        }
    }
    
    public String GetReciveMessage(Socket client) {  
        byte recv[] = new byte[this.MaxBuffer];
        InputStream input = client.getInputStream();
        int size = input.read(recv);

        if( size < 0)
            return "The message could not be found.";

        return new String(recv, false, size);
    }

    public static void main(String args[]) {

    }

}
