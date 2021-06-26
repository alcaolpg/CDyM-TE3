/*
 * UART_con_buffers.h
 *
 * Created: 23/06/2021 15:48:54
 *  Author: Agustín
 */ 


#ifndef UART_CON_BUFFERS_H_
#define UART_CON_BUFFERS_H_
	void uart_cb_init(unsigned char serial_port_value);
	void uart_cb_listo_para_transmitir();
	void uart_cb_transmision_completa();
	char uart_cb_isr_rx();
	void uart_cb_ultima_recepcion(char *paquete);
	void uart_cb_isr_tx();
	void uart_cb_preparar_transmision(char *paquete);




#endif /* UART_CON_BUFFERS_H_ */