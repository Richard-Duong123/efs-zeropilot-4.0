#include "spi_iface.hpp"

void spiCsLow(const SpiCommonDevice_t& device) {
	HAL_GPIO_WritePin(device.csGPIOPort, device.csGPIOPin, 0);
}

void spiCsHigh(const SpiCommonDevice_t& device) {
	HAL_GPIO_WritePin(device.csGPIOPort, device.csGPIOPin, 1);

}

// function to transmit
ZP_Error spiTransmitData(const SpiCommonDevice_t& device, uint8_t* txBuf, uint16_t size, uint32_t timeout) {
	// Checking if the pointers will be nullptrs or not
	if (txBuf == nullptr || device.hspi == nullptr) {
		return ZP_ERROR_NULLPTR;
	}

	spiCsLow(device);
	HAL_StatusTypeDef status = HAL_SPI_Transmit(device.hspi, txBuf, size, timeout);
	spiCsHigh(device);

	if (status == HAL_OK) {
		return ZP_ERROR_OK;
	}
	return ZP_ERROR_EXT_API | ZP_ERROR_FAIL;
}


// Function to receive data
ZP_Error spiTransmitReceiveData(const SpiCommonDevice_t& device, uint8_t* txBuf, uint8_t* rxBuf, uint16_t size, uint32_t timeout) {
	if (txBuf == nullptr || rxBuf == nullptr || device.hspi == nullptr) {
		return ZP_ERROR_NULLPTR;
	}

	spiCsLow(device);
	HAL_StatusTypeDef status = HAL_SPI_TransmitReceive(device.hspi, txBuf, rxBuf, size, timeout);
	spiCsHigh(device);

	if (status == HAL_OK) {
		return ZP_ERROR_OK;
	}
	return ZP_ERROR_EXT_API | ZP_ERROR_FAIL;
}

// Function for SPI transmit and receive
ZP_Error spiTransmitReceiveDataDMA(const SpiCommonDevice_t& device, uint8_t* txData, uint8_t* rxData, uint16_t size) {
	if (txBuf == nullptr || rxBuf == nullptr || device.hspi == nullptr) {
		return ZP_ERROR_NULLPTR;
	}

	spiCsLow(device);
	HAL_StatusTypeDef status = HAL_SPI_TransmitReceive_DMA(device.hspi, txBuf, rxBuf, size, timeout);

	// only turns CS line high if status is not ok
	if (status != HAL_OK) {
		return ZP_ERROR;
	}

	if (status == HAL_OK) {
		return ZP_ERROR_EXT_API | ZP_ERROR_FAIL;
	}
	return ZP_ERROR_OK;
}
