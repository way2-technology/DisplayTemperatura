var http = require("http");
var https = require("https");

const port = process.env.PORT || 8078

const url = "https://api.temperaturaaqui.com.br/temperatura/device?id=80ad9145b5494e2280f5cbcdefdf775d";

const requestTemperature = () => {
    return new Promise((resolve, reject) => {
        https.get(
            url,
            response => {
                let data = "";

                response.on("data", chunk => {
                    data += chunk;
                });

                response.on("end", () => {
                    const parsedData = JSON.parse(data);
                    resolve(Math.round(parsedData.t));
                });
            }
        ).on("error", reject);
    });
};

var server = http.createServer(async function(request, response) {
    response.writeHead(200, {
        "Content-Type": "text/plain"
    });
    if (request.method == "GET") {
        try {
            const value = await requestTemperature();
            const valueString = value.toString();
            const paddedValue = valueString.padStart(2, '0');

            response.end(paddedValue);
        } catch (e) {
            response.end("Error on request");
        }
    } else {
        response.end("Undefined request");
    }
});

server.listen(port);
console.log(`Server running on port ${port}`);
