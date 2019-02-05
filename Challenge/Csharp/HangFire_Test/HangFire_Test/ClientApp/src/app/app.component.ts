import { Component, OnInit } from '@angular/core';
import { HubConnection, LogLevel, HubConnectionBuilder } from '@aspnet/signalr';
import { HttpClient } from '@angular/common/http';

export class EventNotifications {
  public title: string;
  public message: string;
}

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent implements OnInit {
  title = 'app';
  private hubConnection: HubConnection;
  public Messages: Array<EventNotifications>;
  public JobTimer: number;

  constructor(private _http: HttpClient) {
    this.Messages = new Array<EventNotifications>();
  }

  // Send a job into HangFire Endpoint
  public SendJob() {
    this._http.post('https://localhost:44355/api/Jobs/AddJob',
      {Time: this.JobTimer}).subscribe();
  }

  ngOnInit() {
    const builder = new HubConnectionBuilder();
    this.hubConnection = builder.withUrl('https://localhost:44355/NotificationsHub')
      .configureLogging(LogLevel.Information)
      .build();
    this.hubConnection.start().then(_ => { }).catch(err => { console.error(err); });
    this.hubConnection.on('Notifications', (message: EventNotifications) => {
      console.log(message);
      this.Messages.push(message);
    });
  }
}
