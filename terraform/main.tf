# terraform/main.tf
provider "aws" {
  region = "us-west-2"
}

resource "aws_instance" "app_server" {
  ami           = "ami-0c55b159cbfafe1f0"
  instance_type = "t2.micro"

  tags = {
    Name = "HFTTradingServer"
  }

  provisioner "remote-exec" {
    inline = [
      "sudo docker run -d -p 8080:8080 hft_trading_system"
    ]
  }
}

