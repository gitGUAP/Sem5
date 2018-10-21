const kafka = require("kafka-node");
const uuid = require("uuid");

const client = new kafka.Client("localhost:2181", "my-client-id", {
  sessionTimeout: 300,
  spinDelay: 100,
  retries: 2
});

const producer = new kafka.HighLevelProducer(client);
producer.on("ready", function() {
  console.log("Kafka Producer is connected and ready.");
  KafkaService.sendRecord()
});

// For this demo we just log producer errors to the console.
producer.on("error", function(error) {
  console.error(error);
});

const KafkaService = {
    sendRecord: (callback = () => {}) => {
 
        const buffer = new Buffer.from(JSON.stringify("fsdfsdf"));
 
        // Create a new payload
        const record = [
            {
                topic: "webevents.dev",
                messages: buffer,
                attributes: 1 /* Use GZip compression for the payload */
            }
        ];
 
        //Send record to Kafka and log result/error
        producer.send(record, callback);
    }
};
 
