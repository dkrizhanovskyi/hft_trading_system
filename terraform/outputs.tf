# terraform/outputs.tf
output "instance_ip" {
  description = "IP address of the EC2 instance"
  value       = aws_instance.app_server.public_ip
}
