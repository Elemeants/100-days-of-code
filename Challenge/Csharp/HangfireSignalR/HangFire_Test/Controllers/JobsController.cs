using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using Hangfire;
using HangFire_Test.Hubs;
using HangFire_Test.Models;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.SignalR;

namespace HangFire_Test.Controllers
{
    public class ReciberData
    {
        public int Time { get; set; }
    }
    [Route("api/[controller]")]
    [ApiController]
    public class JobsController : ControllerBase
    {
        private readonly IHubContext<NotificationsHub> hubContext;

        public JobsController(IHubContext<NotificationsHub> hubContext)
        {
            this.hubContext = hubContext;
        } 
        [HttpPost("[action]")]
        public IActionResult AddJob([FromBody] ReciberData data)
        {
            BackgroundJob.Enqueue(() => this.Work(data.Time));
            return Ok();
        }

        public void Work(int timer)
        {
            // Sleep time simulation of the timer
            Thread.Sleep(timer * 1000);
            // Sends the notification to the hub
            this.hubContext.Clients.All.SendAsync("Notifications", new EventNotification() {
                Title = "Finished Job",
                Message = "Finished after " + timer.ToString() + " seconds"
            });
        }
    }
}