%ifndef CCHARS_INC
%define CCHARS_INC

%define NUL 00h ; Null    
%define SOH 01h ; Start of header    
%define STX 02h ; Start of text    
%define ETX 03h ; End of text    
%define EOT 04h ; End of transmission    
%define ENQ 05h ; Enquiry    
%define ACK 06h ; Acknowledgment    
%define BEL 07h ; Bell    
%define BS  08h ; Backspace    
%define HT  09h ; Horizontal tab    
%define LF  0Ah ; Line feed    
%define VT  0Bh ; Vertical tab    
%define FF  0Ch ; Form feed    
%define CR  0Dh ; Carriage return    
%define SO  0Eh ; Shift out    
%define SI  0Fh ; Shift in    
%define DLE 10h ; Data link escape    
%define DC1 11h ; Device control 1    
%define DC2 12h ; Device control 2    
%define DC3 13h ; Device control 3    
%define DC4 14h ; Device control 4    
%define NAK 15h ; Negative acknowledgment    
%define SYN 16h ; Synchronous idle    
%define ETB 17h ; End of transmission block    
%define CAN 18h ; Cancel    
%define EM  19h ; End of medium    
%define SUB 1Ah ; Substitute character    
%define ESC 1Bh ; Escape    
%define FS  1Ch ; File separator    
%define GS  1Dh ; Group separator    
%define RS  1Eh ; Record separator    
%define US  1Fh ; Unit separator    
%define DEL FFh ; Delete

%endif ; CCHARS_INC
