FROM epitechcontent/epitest-docker

COPY ./tests/requirements.txt /app/tests/requirements.txt

RUN pip3 install -r /app/tests/requirements.txt

COPY . /app

WORKDIR /app

RUN make