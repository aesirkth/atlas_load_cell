#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/logging/log.h>
/* this is for getting the SENSOR_CHAN_FORCE*/
#include "../modules/nau7802_loadcell/drivers/sensor/nau7802_loadcell/nau7802_loadcell.h"

/* Declare the membership in registered logging module*/
LOG_MODULE_REGISTER(LOADCELL_TEST, CONFIG_SENSOR_LOG_LEVEL);

static int process_sensor_value(const struct device *dev)
{
	struct sensor_value force;
	int ret;

	ret = sensor_sample_fetch(dev);
	if (ret != 0) {
		LOG_ERR("ret: %d, Sensor sample update error", ret);
		return ret;
	}

	ret = sensor_channel_get(dev, SENSOR_CHAN_FORCE, &force);
	if (ret != 0) {
		LOG_ERR("ret: %d, Cannot read NAU7802 force channelr", ret);
		return ret;
	}

	LOG_INF("Force:%f", sensor_value_to_double(&force));
	return 0;
}

static void nau7802_loadcell_handler(const struct device *dev,
			   const struct sensor_trigger *trig)
{
	process_sensor_value(dev);
}

void test_loadcell(void)
{
    	/* Get the device pointer to nau7802 sensor*/
	const struct device *const nau7802 = DEVICE_DT_GET_ONE(nuvoton_nau7802_loadcell);

	if (!device_is_ready(nau7802)) {
		LOG_ERR("sensor: device not ready.");
		return;
	}

	/* set the offset and calibration factor*/
	float32_t offset = 2.505000511475965652e+01;
	float32_t calibFactor = 6.527824679590503775e-06;
	struct sensor_value offset_attri;
	struct sensor_value calib_attri;

	/* Currently don't have a good way to pass floating point value to the sensor driver*/
	/* Use the memcpy to do bit-to-bit copy, from float32_t to int32_t*/
	memcpy(&offset_attri.val1, &offset, sizeof(offset));
	memcpy(&calib_attri.val1, &calibFactor, sizeof(calibFactor));

	if(sensor_attr_set(nau7802, SENSOR_CHAN_FORCE, SENSOR_ATTR_OFFSET, &offset_attri) != 0){
		LOG_ERR("Cannot configure the offset");
		return;
	}

	if(sensor_attr_set(nau7802, SENSOR_CHAN_FORCE, SENSOR_ATTR_CALIBRATION, &calib_attri) != 0){
		LOG_ERR("Cannot configure the offset");
		return;
	}

	/* Set the tragger type and handler function if needed*/
	if (IS_ENABLED(CONFIG_NAU7802_LOADCELL_TRIGGER)) {
		struct sensor_trigger trig = {
			.type = SENSOR_TRIG_DATA_READY,
			.chan = SENSOR_CHAN_ALL,
		};
		if (sensor_trigger_set(nau7802, &trig, nau7802_loadcell_handler) < 0) {
			LOG_ERR("Cannot configure trigger");
			return;
		}
	}
	
	while (!IS_ENABLED(CONFIG_NAU7802_LOADCELL_TRIGGER)) {
		process_sensor_value(nau7802);
		k_sleep(K_MSEC(2000));
	}
	k_sleep(K_FOREVER);


}

int main() {
	test_loadcell();
	return 0;
}
